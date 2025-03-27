using System;
using WEB_153504_Skroba.Domain.Entities;

namespace WEB_153504_Skroba.BlazorWasm.Services
{
    public interface IDataService
    {
        event Action DataLoaded;

        List<Category> Categories { get; set; }

        List<Tea> ObjectsList { get; set; }

        bool Success { get; set; }

        string ErrorMessage { get; set; }

        int TotalPages { get; set; }

        int CurrentPage { get; set; }

        public Task GetProductListAsync(string? categoryNormalizedName, int pageNo = 1);

        public Task<Tea> GetProductByIdAsync(int id);

        public Task GetCategoryListAsync();
    }
}

