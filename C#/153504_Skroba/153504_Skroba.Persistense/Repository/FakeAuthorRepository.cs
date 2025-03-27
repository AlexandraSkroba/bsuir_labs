using _153504_Skroba.Domain.Abstractions;
using _153504_Skroba.Domain.Entities;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Linq.Expressions;
using System.Text;
using System.Threading.Tasks;

namespace _153504_Skroba.Persistense.Repository
{
    public class FakeAuthorRepository : IRepository<Author>
    {
        List<Author> _authors;
        public FakeAuthorRepository()
        {
            _authors = new List<Author>()
            {
                new Author(){ Id=1, Name = "Саша Скроба", Books = new List<Book>()},
                new Author(){ Id=2, Name = "Егор Дуралейко", Books=new List<Book>()}
            };
        }

        public Task<Author> GetByIdAsync(int id, CancellationToken cancellationToken = default,
            params Expression<Func<Author, object>>[]? includesProperties)
        {
            throw new NotImplementedException();
        }

        public async Task<IReadOnlyList<Author>> ListAllAsync(CancellationToken cancellationToken = default)
        {
            return await Task.Run(() => _authors);
        }

        public Task<IReadOnlyList<Author>> ListAsync(Expression<Func<Author, bool>>? filter,
            CancellationToken cancellationToken = default, params Expression<Func<Author, object>>[] includesProperties)
        {
            throw new NotImplementedException();
        }

        public Task AddAsync(Author author, CancellationToken cancellationToken = default)
        {
            throw new NotImplementedException();
        }

        public Task UpdateAsync(Author author, CancellationToken cancellationToken = default)
        {
            throw new NotImplementedException();
        }

        public Task DeleteAsync(Author author, CancellationToken cancellationToken = default)
        {
            throw new NotImplementedException();
        }

        public Task<Author> FirstOrDefaultAsync(Expression<Func<Author, bool>> filter, CancellationToken cancellationToken = default)
        {
            throw new NotImplementedException();
        }

    }
}
