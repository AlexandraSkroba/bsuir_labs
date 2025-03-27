using System.Data.SqlTypes;
using System.Net.Http;
using System.Text;
using System.Text.Json;
using WEB_153504_Skroba.Domain.Entities;
using WEB_153504_Skroba.Domain.Models;
using WEB_153504_Skroba.Services.ProductService;
using WEB_153504_Skroba.Services.TeaService;
using System.Net.Http.Headers;
using Microsoft.AspNetCore.Authentication;

namespace WEB_153504_Skroba.Services.ApiService
{
	public class ApiTeaService : ITeaService
	{
		private readonly HttpClient _httpClient;
		private readonly ILogger<ApiTeaService> _logger;
		private readonly string _pageSize;
		private readonly JsonSerializerOptions _serializerOptions;
        private readonly HttpContext _httpContext;

        public ApiTeaService(HttpClient httpClient, IConfiguration configuration, ILogger<ApiTeaService> logger, IHttpContextAccessor httpContextAccessor)
        {
            _httpClient = httpClient;
            _pageSize = configuration.GetSection("Pagination:ItemsPerPage").Value;
            _serializerOptions = new JsonSerializerOptions()
            {
                PropertyNamingPolicy = JsonNamingPolicy.CamelCase
            };
            _logger = logger;
            _httpContext = httpContextAccessor.HttpContext;
        }
        public async Task<ResponseData<Tea>> CreateProductAsync(Tea product, IFormFile? formFile)
		{
            AddTokenToHeader();
            var urlString = new StringBuilder($"{_httpClient.BaseAddress!.AbsoluteUri}teas/");
            var response = await _httpClient.PostAsJsonAsync(urlString.ToString(), product, _serializerOptions);

            if (response.IsSuccessStatusCode)
			{
                var teaResponse = await response.Content.ReadFromJsonAsync<ResponseData<Tea>>(_serializerOptions);
                if (formFile != null)
                {
                    await SaveImageAsync(teaResponse.Data.Id, formFile);
                }

                return new ResponseData<Tea>
                {
                    Data = teaResponse.Data,
                    Success = true
                };
            }
			_logger
			.LogError($"-----> object not created. Error: {response.StatusCode.ToString()}");
			return new ResponseData<Tea>
			{
				Success = false,
				ErrorMessage = $"Объект не добавлен. Error: {response.StatusCode.ToString()}"
			};
		}

		public async Task DeleteProductAsync(int id)
		{
            AddTokenToHeader();
            var urlString = new StringBuilder($"{_httpClient.BaseAddress?.AbsoluteUri}Teas/delete/{id}");

			await _httpClient.DeleteAsync(urlString.ToString());
		}

		public async Task<ResponseData<Tea?>> GetProductByIdAsync(int id)
		{
            var urlString = new StringBuilder($"{_httpClient.BaseAddress!.AbsoluteUri}teas/id/{id}");
			var response = await _httpClient.GetAsync(new Uri(urlString.ToString()));

			if (response.IsSuccessStatusCode)
			{
				try
				{
					var a = await response.Content.ReadFromJsonAsync<ResponseData<Tea>>(_serializerOptions);
					return a;
				}
				catch (JsonException ex)
				{
					_logger.LogError($"-----> Ошибка: {ex.Message}");
					return new ResponseData<Tea>
					{
						Success = false,
						ErrorMessage = $"Ошибка: {ex.Message}"
					};
				}
			}
			_logger.LogError($"-----> Данные не получены от сервера. Error:{response.StatusCode}");
			return new ResponseData<Tea>()
			{
				Success = false,
				ErrorMessage = $"Данные не получены от сервера. Error:{response.StatusCode}"
			};
		}

		public async Task<ResponseData<ListModel<Tea>>> GetProductListAsync(string? categoryNormalizedName, int pageNo = 1)
		{
            AddTokenToHeader();
            // подготовка URL запроса
            var urlString= new StringBuilder($"{_httpClient.BaseAddress.AbsoluteUri}teas/");
			// добавить категорию в маршрут
			if (categoryNormalizedName != null)
			{
				urlString.Append($"{categoryNormalizedName}/");
			};
			// добавить номер страницы в маршрут
			if (pageNo > 1)
			{
				urlString.Append($"{pageNo}");
			};
			// добавить размер страницы в строку запроса
			if (!_pageSize.Equals("3"))
			{
				urlString.Append(QueryString.Create("pageSize", _pageSize));
			}
			// отправить запрос к API
			var response = await _httpClient.GetAsync(new Uri(urlString.ToString()));
			if (response.IsSuccessStatusCode)
			{
				try
				{
					return await response.Content.ReadFromJsonAsync<ResponseData<ListModel<Tea>>>(_serializerOptions);
				}
				catch (JsonException ex)
				{
					_logger.LogError($"-----> Ошибка: {ex.Message}");
					return new ResponseData<ListModel<Tea>>
					{
						Success = false,
						ErrorMessage = $"Ошибка: {ex.Message}"
					};
				}
			}
			_logger.LogError($"-----> Данные не получены от сервера. Error: {response.StatusCode.ToString()}");
			return new ResponseData<ListModel<Tea>>
			{
				Success = false,
				ErrorMessage = $"Данные не получены от сервера. Error: {response.StatusCode.ToString()}"
			};
		}

		public async Task UpdateProductAsync(int id, Tea product, IFormFile? formFile)
		{
            AddTokenToHeader();
            var urlString = new StringBuilder($"{_httpClient.BaseAddress!.AbsoluteUri}teas/put/{id}");
            await _httpClient.PutAsJsonAsync(urlString.ToString(), product, _serializerOptions);

            if (formFile != null)
            {
                await SaveImageAsync(id, formFile);
            }
        }

        private async Task SaveImageAsync(int id, IFormFile image)
        {
            AddTokenToHeader();
            var request = new HttpRequestMessage
            {
                Method = HttpMethod.Post,
                RequestUri = new Uri($"{_httpClient.BaseAddress?.AbsoluteUri}teas/{id}")
            };
            var content = new MultipartFormDataContent();
            var streamContent = new StreamContent(image.OpenReadStream());
            content.Add(streamContent, "formFile", image.FileName);
            request.Content = content;
            await _httpClient.SendAsync(request);
        }

        private async void AddTokenToHeader()
        {
            var token = await _httpContext.GetTokenAsync("access_token");
            _httpClient.DefaultRequestHeaders.Authorization = new AuthenticationHeaderValue("bearer", token);
        }
    }
}
