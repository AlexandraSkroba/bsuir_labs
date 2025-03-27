
using System.ComponentModel.DataAnnotations;

namespace WEB_153504_Skroba.Domain.Entities
{
	public class Category
	{
		[Key]
		public int Id { get; set; }
		public string? Name { get; set; }
		public required string? NormalizedName { get; set; }
	}
}
