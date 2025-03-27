
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;
using System.Runtime.InteropServices;

namespace WEB_153504_Skroba.Domain.Entities
{
	public class Tea
	{
		[Key]
		public int Id { get; set; } // Уникальный номер
		[ForeignKey("Category")]
		public int CategoryId { get; set; }
		public string? Name { get; set; } // Название
		public string? Description { get; set; } // Описание
		public Category? Category { get; set; } // Категория
		public decimal Price { get; set; } // Цена
		public string? ImagePath { get; set; } // Путь к файлу изображения
		public string? ImageMimeType { get; set; } // Mime тип изображения
	}
}
