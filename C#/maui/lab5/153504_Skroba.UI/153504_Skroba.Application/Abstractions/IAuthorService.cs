using _153504_Skroba.Domain.Entities;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _153504_Skroba.Application.Abstractions
{
    public interface IAuthorService : IBaseService<Author>
    {
        public Task<IReadOnlyList<Book>> GetAllBooksByAuthorAsync(int id);
        public Task AddBookByAuthor(int authorId, Book book);
    }
}
