using Microsoft.AspNetCore.Mvc;
using Moq;
using WEB_153504_Skroba.Controllers;
using WEB_153504_Skroba.Domain.Entities;
using WEB_153504_Skroba.Services.ProductService;
using WEB_153504_Skroba.Services.CategoryService;
using WEB_153504_Skroba.Domain.Models;
using Microsoft.AspNetCore.Http;

namespace WEB_153504_Skroba.Tests
{
    public class TeaControllerTests
    {
        [Fact]
        public async Task Index_ReturnsNotFound_WhenCategoryListNotSuccessful()
        {
            // Arrange
            var mockTeaService = new Mock<ITeaService>(); // �������� ���-������� ��� ���������� ITeaService � ICategoryService
            var mockCategoryService = new Mock<ICategoryService>();

            mockCategoryService
                .Setup(service => service.GetCategoryListAsync()) // ��������� ���-�������, ��������, ��� ��� ������ ������ GetCategoryListAsync ������ ������������ ���������� ���������
                .ReturnsAsync(new ResponseData<List<Category>> { Success = false, ErrorMessage = "������ ��� ��������� ������ ���������" }); // ������� ����������� ���������� � ���������� �� ������

            var controller = new TeaController(mockTeaService.Object, mockCategoryService.Object); // �������� �����������, ��������� ���-������� � �����������

            // Act
            // ����� ������ Index ����������� � ��������� null � ��������� category � 1 � ��������� pageno
            var result = await controller.Index(null, 1);

            // Assert
            // ��������, ��� ��������� �������� �������� ���� NotFoundObjectResult
            var notFoundResult = Assert.IsType<NotFoundObjectResult>(result);
            // ��������, ��� �������� ��������� �� ������ � NotFoundObjectResult ������������� ����������
            Assert.Equal("������ ��� ��������� ������ ���������", notFoundResult.Value);
        }

        [Fact]
        public async Task Index_ReturnsNotFound_WhenProductListNotSuccessful()
        {
            // Arrange
            var mockTeaService = new Mock<ITeaService>();
            var mockCategoryService = new Mock<ICategoryService>();

            mockCategoryService.Setup(s => s.GetCategoryListAsync())
               .ReturnsAsync(new ResponseData<List<Category>> { Success = true, Data = new List<Category>() });

            mockTeaService.Setup(s => s.GetProductListAsync(null, 1))
                .ReturnsAsync(new ResponseData<ListModel<Tea>> { Success = false, ErrorMessage = "������ ��� ��������� ������ ���������" });


            var controller = new TeaController(mockTeaService.Object, mockCategoryService.Object);

            // Act
            var result = await controller.Index(null, 1);

            // Assert
            Assert.IsType<NotFoundObjectResult>(result);
        }

        [Fact]
        public async Task Index_ReturnsCategoriesInViewData_WhenSuccessful()
        {
            // Arrange
            var mockTeaService = new Mock<ITeaService>();
            var mockCategoryService = new Mock<ICategoryService>();
            var mockHttpContext = new Mock<HttpContext>();
            var categories = new List<Category>() {
                    new Category { Id = 1, Name = "Name", NormalizedName = "name" }
                };
            var currentCategory = "���";

            mockCategoryService.Setup(s => s.GetCategoryListAsync())
               .ReturnsAsync(new ResponseData<List<Category>> { Data = categories });
            mockTeaService.Setup(s => s.GetProductListAsync(null, 1))
                .ReturnsAsync(new ResponseData<ListModel<Tea>> { Data = new ListModel<Tea>() { Items = new List<Tea>() { new Tea { Id = 1, Name = "Product", Description = "Description", Price = 10 } } } });
            mockHttpContext.Setup(c => c.Request.Headers)
                .Returns(new HeaderDictionary { { "X-Requested-With", "XMLHttpRequest" } });

            var controllerContext = new ControllerContext
            {
                HttpContext = mockHttpContext.Object
            };

            var controller = new TeaController(mockTeaService.Object, mockCategoryService.Object)
            {
                ControllerContext = controllerContext
            };

            // Act
            var result = await controller.Index(null, 1);

            // Assert
            Assert.True(categories.SequenceEqual(controller.ViewData["categories"] as List<Category>));
            Assert.Equal(currentCategory, controller.ViewData["currentCategory"]);
            Assert.IsType<ListModel<Tea>>(controller.ViewData.Model);
        }
    }
}