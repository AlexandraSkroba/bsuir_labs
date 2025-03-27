using Microsoft.EntityFrameworkCore;
using WEB_153504_Skroba.Domain.Entities;
using WEB_153504_Skroba.API.Data;

namespace WEB_153504_Skroba.API.Data
{
    public class DbInitializer
    {
        public static async Task SeedData(WebApplication app)
        {
            // Получение контекста БД
            using var scope = app.Services.CreateScope();
            var context = scope.ServiceProvider.GetRequiredService<AppDbContext>();
            var imageBaseUrl = app.Configuration.GetSection("ImageSettings:ImageUrl").Get<string>();
            // Выполнение миграций
            await context.Database.MigrateAsync();

            if (!context.Teas.Any())
            {
                var _teas = new List<Tea> {
                new Tea {
                    Name = "Сенча",
                    Description = "Зеленый чай \"Сенча\" обладает освежающим и нежным вкусом с легкой горчинкой и сладковатыми нотками. " +
                    "Аромат чая часто описывается как травяной и цветочный.",
                    Category = context.Categories.FirstOrDefault(c => c.NormalizedName == "green"),
                    Price = 50,
                    ImagePath = $"{imageBaseUrl}/tee1.jpg" },
                new Tea {
                    Name = "Гюйсюн",
                    Price = 70,
                    ImagePath = $"{imageBaseUrl}/greenTea2.jpg",
                    Description = "Нежный, цветочный вкус с легкими фруктовыми нотками. Аромат свежий и сладкий.",
                    Category = context.Categories.FirstOrDefault(c => c.NormalizedName == "green") },
                new Tea {
                    Name = "Ассам",
                    Description = "Крепкий, насыщенный вкус с медовыми и ореховыми нотками. Аромат пряный и сладковатый.",
                    Category = context.Categories.FirstOrDefault(c => c.NormalizedName == "black"),
                    Price = 50,
                    ImagePath = $"{imageBaseUrl}/blackTea1.jpg"},
                new Tea {
                    Name = "Би Ло Чунь",
                    Description = "Освежающий, с ярко выраженным цветочным вкусом и ароматом, с нотами апельсина.",
                    Category = context.Categories.FirstOrDefault(c => c.NormalizedName == "green"),
                    Price = 60,
                    ImagePath = $"{imageBaseUrl}/greenTea2.jpg"},
                new Tea {
                    Name = "Тайпин Хоукуи",
                    Description = "Очень нежный, с травяными и медовыми нотками во вкусе и аромате.",
                    Category = context.Categories.FirstOrDefault(c => c.NormalizedName == "green"),
                    Price = 65,
                    ImagePath = $"{imageBaseUrl}/tee1.jpg"},
                new Tea {
                    Name = "Дарджилинг",
                    Description = "Нежный, с фруктовыми и цветочными нотками во вкусе и аромате.",
                    Category = context.Categories.FirstOrDefault(c => c.NormalizedName == "black"),
                    Price = 70,
                    ImagePath = $"{imageBaseUrl}/blackTea1.jpg"},
                new Tea {
                    Name = "Цейлон",
                    Description = "Средней крепости, с яркими цветочными и фруктовыми оттенками. Аромат свежий и травянистый.",
                    Category = context.Categories.FirstOrDefault(c => c.NormalizedName == "black"),
                    Price = 60,
                    ImagePath = $"{imageBaseUrl}/blackTea1.jpg"},
                new Tea {
                    Name = "Цветущий чай",
                    Description = "Легкий и нежный вкус с фруктовыми и цветочными оттенками. Аромат свежий и ароматный.",
                    Category = context.Categories.FirstOrDefault(c => c.NormalizedName == "greenconn"),
                    Price = 100,
                    ImagePath = $"{imageBaseUrl}/blackTea1.jpg"},
                new Tea {
                    Name = "Бубль Гунфу",
                    Description = "Освежающий вкус с травяными и миндальными нотками. Аромат травянистый и нежный.",
                    Category = context.Categories.FirstOrDefault(c => c.NormalizedName == "greenconn"),
                    Price = 70,
                    ImagePath = $"{imageBaseUrl}/blackTea1.jpg"},
                new Tea {
                    Name = "Аньцзи Чунцзянь",
                    Description = "Очень нежный, с нотами свежей зелени и с легкими цветочными нюансами вкуса и аромата.",
                    Category = context.Categories.FirstOrDefault(c => c.NormalizedName == "greenconn"),
                    Price = 85,
                    ImagePath = $"{imageBaseUrl}/blackTea1.jpg"},
				};

                context.Teas.AddRange(_teas);
                await context.SaveChangesAsync();
            }


            if (!context.Categories.Any())
            {
                var _categories = new List<Category> {
                    new Category {Name="Зеленый чай", NormalizedName="green"},
                    new Category {Name="Черный чай", NormalizedName="black"},
                    new Category {Name="Зеленый связанный чай", NormalizedName="greenconn"},
            };

                context.Categories.AddRange(_categories);
                await context.SaveChangesAsync();
            }
        }
    }
}

