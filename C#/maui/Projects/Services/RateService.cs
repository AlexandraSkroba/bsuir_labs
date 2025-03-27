using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.Json;
using System.Threading.Tasks;
using Projects.Entities;
using System.Diagnostics;

namespace Projects.Services
{
    class RateService : IRateService
    {
        private readonly HttpClient _httpClient;
        private readonly List<int> _ArrayOfCurrenciesId = new List<int>() { 456, 451, 431, 426, 462, 429 };
        public RateService(HttpClient httpClient)
        {
            _httpClient= httpClient;
        }

        public async Task<IEnumerable<Rate>> GetRates(DateTime date)
        {
            var RateItems = new List<Rate>();
            
            try
            {
                var response = await _httpClient.GetAsync(_httpClient.BaseAddress + $"?ondate={date:yyyy-M-d}&periodicity=0");
                if (response.IsSuccessStatusCode)
                {
                    string content = await response.Content.ReadAsStringAsync();
                    RateItems = JsonSerializer.Deserialize<List<Rate>>(content);
                }
            }
            catch (Exception ex)
            {
                Debug.WriteLine(@"\tERROR {0}", ex.Message);
            }

            return RateItems.Where(x => _ArrayOfCurrenciesId.Contains(x.Cur_ID));
        }
    }
}
