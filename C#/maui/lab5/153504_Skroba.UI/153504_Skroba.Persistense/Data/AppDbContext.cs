using Microsoft.EntityFrameworkCore;
using _153504_Skroba.Domain.Entities;

namespace _153504_Skroba.Persistense.Data
{
    public class AppDbContext : DbContext
    {
        public DbSet<Author> Authors { get; set; }
        public DbSet<Book> Books { get; set; }
        public AppDbContext(DbContextOptions<AppDbContext> options) : base(options)
        {
            Database.EnsureCreated();
        }
    }
}
