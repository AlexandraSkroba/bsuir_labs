using System.Text;
using System.Text.Json;
using WEB_153504_Skroba.Domain.Entities;
using WEB_153504_Skroba.Domain.Models;
using WEB_153504_Skroba.Services.CategoryService;

namespace WEB_153504_Skroba.Services.ApiService
{
	public class ApiCategoryService : ICategoryService
	{
		private readonly HttpClient _httpClient;
		private readonly ILogger _logger;
		private readonly JsonSerializerOptions _serializerOptions;

		public ApiCategoryService(HttpClient httpClient, IConfiguration configuration, ILogger<ApiCategoryService> logger)
		{
			_httpClient = httpClient;
			_serializerOptions = new JsonSerializerOptions()
			{
				PropertyNamingPolicy = JsonNamingPolicy.CamelCase
			};
			_logger = logger;
		}
		public async Task<ResponseData<List<Category>>> GetCategoryListAsync()
		{
			var urlString = new StringBuilder($"{_httpClient.BaseAddress?.AbsoluteUri}Categories/");

            var response = await _httpClient.GetAsync(new Uri(urlString.ToString()));

			if (response.IsSuccessStatusCode)
			{
				try
				{
					var responseData = await response.Content.ReadFromJsonAsync<ResponseData<List<Category>>>(_serializerOptions);

					if (responseData != null)
					{
						return responseData;
					}
					else
					{
						_logger.LogError($"-----> Ошибка: Данные не удалось десериализовать.");
						return new ResponseData<List<Category>>
						{
							Success = false,
							ErrorMessage = $"Ошибка: Данные не удалось десериализовать."
						};
					}
				}
				catch (JsonException ex)
				{
					_logger.LogError($"-----> Ошибка: {ex.Message}");
					return new ResponseData<List<Category>>
					{
						Success = false,
						ErrorMessage = $"Ошибка: {ex.Message}"
					};
				}
			}
			else
			{
				_logger.LogError($"-----> Данные не получены от сервера. Error: {response.StatusCode}");
				return new ResponseData<List<Category>>
				{
					Success = false,
					ErrorMessage = $"Данные не получены от сервера. Error: {response.StatusCode}"
				};
			}
		}
	}
}
