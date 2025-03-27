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
    public class FakeBookRepository : IRepository<Book>
    {
        List<Book> _list = new List<Book>();
        public FakeBookRepository()
        {
            Random rand = new Random();
            int k = 1;
            for (int i = 1; i <= 2; i++)
                for (int j = 0; j < 10; j++)
                    _list.Add(new Book() { Id = k, Name = $"Work{k}", Title = $"Book {k++}", Description = $"Description {i}.{j}", Rating = rand.NextDouble() * 10 });
        }

        public Task<Book> GetByIdAsync(int id, CancellationToken cancellationToken = default,
            params Expression<Func<Book, object>>[]? includesProperties)
        {
            throw new NotImplementedException();
        }

        public Task<IReadOnlyList<Book>> ListAllAsync(CancellationToken cancellationToken = default)
        {
            throw new NotImplementedException();
        }

        public async Task<IReadOnlyList<Book>> ListAsync(Expression<Func<Book, bool>> filter, CancellationToken cancellationToken = default, params Expression<Func<Book, object>>[]? includesProperties)
        {
            var data = _list.AsQueryable();
            return data.Where(filter).ToList();
        }

        public Task AddAsync(Book entity, CancellationToken cancellationToken = default)
        {
            throw new NotImplementedException();
        }

        public Task UpdateAsync(Book entity, CancellationToken cancellationToken = default)
        {
            throw new NotImplementedException();
        }

        public Task DeleteAsync(Book entity, CancellationToken cancellationToken = default)
        {
            throw new NotImplementedException();
        }

        public Task<Book> FirstOrDefaultAsync(Expression<Func<Book, bool>> filter, CancellationToken cancellationToken = default)
        {
            throw new NotImplementedException();
        }

    }
}
