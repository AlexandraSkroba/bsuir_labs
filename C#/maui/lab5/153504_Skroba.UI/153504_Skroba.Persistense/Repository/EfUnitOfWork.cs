using _153504_Skroba.Domain.Abstractions;
using _153504_Skroba.Domain.Entities;
using _153504_Skroba.Persistense.Data;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _153504_Skroba.Persistense.Repository
{
    public class EfUnitOfWork : IUnitOfWork
    {
        private readonly AppDbContext _context;
        private readonly Lazy<IRepository<Author>> _authorRepository;
        private readonly Lazy<IRepository<Book>> _bookRepository;

        public EfUnitOfWork(AppDbContext context)
        {
            _context = context;
            _authorRepository = new Lazy<IRepository<Author>>(() => new EfRepository<Author>(context));
            _bookRepository = new Lazy<IRepository<Book>>(() => new EfRepository<Book>(context));
        }

        IRepository<Author> IUnitOfWork.AuthorRepository => _authorRepository.Value;
        IRepository<Book> IUnitOfWork.BookRepository => _bookRepository.Value;
        public async Task CreateDatabaseAsync()
        {
            await _context.Database.EnsureCreatedAsync();
        }
        public async Task RemoveDatbaseAsync()
        {
            await _context.Database.EnsureDeletedAsync();
        }
        public async Task SaveAllAsync()
        {
            await _context.SaveChangesAsync();
        }
    }
}
