using _153504_Skroba.Domain.Abstractions;
using _153504_Skroba.Domain.Entities;
using System.Linq.Expressions;

namespace _153504_Skroba.Persistense.Repository
{
    public class FakeAuthorRepository : IRepository<Author>
    {
        List<Author> _authors;
        public FakeAuthorRepository()
        {
            _authors = new List<Author>()
            {
                new Author()
                {
                    Id=1, Name="Егор Дуралейко", Books = new List<Book>()
                },
                new Author()
                {
                    Id=2, Name="Саша Скробик", Books = new List<Book>()
                }
            };
        }
        public Task AddAsync(Author entity, CancellationToken cancellationToken = default)
        {
            throw new NotImplementedException();
        }

        public Task DeleteAsync(Author entity, CancellationToken cancellationToken = default)
        {
            throw new NotImplementedException();
        }

        public Task<Author> FirstOrDefaultAsync(Expression<Func<Author, bool>> filter, CancellationToken cancellationToken = default)
        {
            throw new NotImplementedException();
        }

        public Task<Author> GetByIdAsync(int id, CancellationToken cancellationToken = default, params Expression<Func<Author, object>>[]? includesProperties)
        {
            throw new NotImplementedException();
        }

        public async Task<IReadOnlyList<Author>> ListAllAsync(CancellationToken cancellationToken = default)
        {
            return await Task.Run(() => _authors);
        }

        public Task<IReadOnlyList<Author>> ListAsync(Expression<Func<Author, bool>> filter, CancellationToken cancellationToken = default, params Expression<Func<Author, object>>[]? includesProperties)
        {
            throw new NotImplementedException();
        }

        public Task UpdateAsync(Author entity, CancellationToken cancellationToken = default)
        {
            throw new NotImplementedException();
        }
    }
}
