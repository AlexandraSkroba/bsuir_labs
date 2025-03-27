using Microsoft.Data.Sqlite;
using Microsoft.EntityFrameworkCore;
using Moq;
using System.Data.Common;
using WEB_153504_Skroba.API.Data;
using WEB_153504_Skroba.API.Services.TeaService;
using WEB_153504_Skroba.Domain.Entities;
using WEB_153504_Skroba.Domain.Models;

namespace WEB_153504_Skroba.Tests
{
    public class ApiTeaServiceTests : IDisposable
    {
        private readonly DbConnection _connection;
        private readonly DbContextOptions<AppDbContext> _contextOptions;

        public ApiTeaServiceTests()
        {
            // Create and open a connection. This creates the SQLite in-memory database, which will persist until the connection is closed
            // at the end of the test (see Dispose below).
            _connection = new SqliteConnection("Filename=:memory:");
            _connection.Open();

            // These options will be used by the context instances in this test suite, including the connection opened above.
            _contextOptions = new DbContextOptionsBuilder<AppDbContext>()
                .UseSqlite(_connection)
                .Options;

            // Create the schema and seed some data
            using var context = new AppDbContext(_contextOptions);

            if (context.Database.EnsureCreated())
            {
                using var viewCommand = context.Database.GetDbConnection().CreateCommand();
                viewCommand.CommandText = @"
                    CREATE VIEW AllResources AS
                    SELECT Url
                    FROM Teas;";
                viewCommand.ExecuteNonQuery();
            }
            context.Categories.AddRange(
                new Category { Name = "Зеленый чай", NormalizedName = "green" },
                new Category { Name = "Черный чай", NormalizedName = "black" },
                new Category { Name = "Зеленый связанный чай", NormalizedName = "greenconn" });
            context.Teas.AddRange(
                new Tea { Name = "Tea 1", Description = "Description 1", Price = 10, CategoryId = 1 },
                new Tea { Name = "Tea 2", Description = "Description 2", Price = 20, CategoryId = 1 },
                new Tea { Name = "Tea 3", Description = "Description 3", Price = 30, CategoryId = 2 },
                new Tea { Name = "Tea 4", Description = "Description 4", Price = 40, CategoryId = 3 },
                new Tea { Name = "Tea 5", Description = "Description 5", Price = 50, CategoryId = 3 },
                new Tea { Name = "Tea 5", Description = "Description 6", Price = 50, CategoryId = 3 },
                new Tea { Name = "Tea 5", Description = "Description 7", Price = 50, CategoryId = 3 },
                new Tea { Name = "Tea 5", Description = "Description 8", Price = 50, CategoryId = 3 },
                new Tea { Name = "Tea 5", Description = "Description 9", Price = 50, CategoryId = 3 },
                new Tea { Name = "Tea 5", Description = "Description 10", Price = 50, CategoryId = 3 },
                new Tea { Name = "Tea 5", Description = "Description 11", Price = 50, CategoryId = 3 },
                new Tea { Name = "Tea 5", Description = "Description 12", Price = 50, CategoryId = 3 },
                new Tea { Name = "Tea 5", Description = "Description 13", Price = 50, CategoryId = 3 },
                new Tea { Name = "Tea 5", Description = "Description 14", Price = 50, CategoryId = 3 },
                new Tea { Name = "Tea 5", Description = "Description 15", Price = 50, CategoryId = 3 },
                new Tea { Name = "Tea 5", Description = "Description 16", Price = 50, CategoryId = 3 },
                new Tea { Name = "Tea 5", Description = "Description 17", Price = 50, CategoryId = 3 },
                new Tea { Name = "Tea 5", Description = "Description 18", Price = 50, CategoryId = 3 },
                new Tea { Name = "Tea 5", Description = "Description 19", Price = 50, CategoryId = 3 },
                new Tea { Name = "Tea 5", Description = "Description 20", Price = 50, CategoryId = 3 },
                new Tea { Name = "Tea 5", Description = "Description 21", Price = 50, CategoryId = 3 });
            context.SaveChanges();
        }
        AppDbContext CreateContext() => new AppDbContext(_contextOptions);
        public void Dispose() => _connection.Dispose();

        [Fact]
        public void ServiceReturnsFirstPageOfThreeItems()
        {
            // Arrange
            using var context = CreateContext();
            var service = new TeaService(context, null, null);

            // Act
            var result = service.GetProductListAsync(null).Result;

            // Assert
            Assert.IsType<ResponseData<ListModel<Tea>>>(result);
            Assert.True(result.Success);
            Assert.Equal(1, result.Data!.CurrentPage);
            Assert.Equal(3, result.Data.Items.Count);
            Assert.Equal(7, result.Data.TotalPages);
            Assert.Equal(context.Teas.First(), result.Data.Items[0]);
        }

        [Fact]
        public void ServiceReturnsRightPageOfThreeItems()
        {
            // Arrange
            using var context = CreateContext();
            var service = new TeaService(context, null, null);

            // Act
            var result = service.GetProductListAsync(null, 2).Result;

            // Assert
            Assert.IsType<ResponseData<ListModel<Tea>>>(result);
            Assert.True(result.Success);
            Assert.Equal(2, result.Data.CurrentPage);
            Assert.Equal(3, result.Data.Items.Count);
            Assert.Equal(7, result.Data.TotalPages);
            Assert.Equal(context.Teas.AsEnumerable().ElementAt(3), result.Data.Items[0]);
            Assert.Equal(context.Teas.AsEnumerable().ElementAt(4), result.Data.Items[1]);
        }

        [Fact]
        public void ServiceFiltersByCategory()
        {
            // Arrange
            using var context = CreateContext();
            var service = new TeaService(context, null, null);

            // Act
            var result = service.GetProductListAsync("green").Result;

            // Assert
            Assert.IsType<ResponseData<ListModel<Tea>>>(result);
            Assert.True(result.Success);
            Assert.Equal(1, result.Data.CurrentPage);
            Assert.Equal(2, result.Data.Items.Count);
            Assert.Equal(1, result.Data.TotalPages);
            Assert.Equal(context.Teas.AsEnumerable().ElementAt(0), result.Data.Items[0]);
            Assert.Equal(context.Teas.AsEnumerable().ElementAt(1), result.Data.Items[1]);
        }

        [Fact]
        public void ServiceSetsMaxPageSize()
        {
            // Arrange
            using var context = CreateContext();
            var service = new TeaService(context, null, null);

            // Act
            var result = service.GetProductListAsync(null, 1, 23).Result;

            // Assert
            Assert.IsType<ResponseData<ListModel<Tea>>>(result);
            Assert.True(result.Success);
            Assert.Equal(1, result.Data.CurrentPage);
            Assert.Equal(20, result.Data.Items.Count);
            Assert.Equal(2, result.Data.TotalPages);
        }

        [Fact]
        public void ServiceReturnsErrorIfPageNoIsIncorrect()
        {
            // Arrange
            using var context = CreateContext();
            var service = new TeaService(context, null, null);

            // Act
            var result = service.GetProductListAsync(null, 4, 23).Result;

            // Assert
            Assert.IsType<ResponseData<ListModel<Tea>>>(result);
            Assert.False(result.Success);
        }
    }
}
