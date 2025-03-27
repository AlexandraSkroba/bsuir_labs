using Microsoft.EntityFrameworkCore;
using WEB_153504_Skroba.Domain.Entities;

namespace WEB_153504_Skroba.API.Data
{
	public class AppDbContext : DbContext
	{
		public AppDbContext(DbContextOptions<AppDbContext> options) : base(options)
		{
		}

		public DbSet<Category> Categories { get; set; }
		public DbSet<Tea> Teas { get; set; }

	}
}
