using _153504_Skroba.Application.Abstractions;
using _153504_Skroba.Domain.Abstractions;
using _153504_Skroba.Domain.Entities;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using _153504_Skroba.Persistense;
using _153504_Skroba.Persistense.Repository;
using _153504_Skroba.Persistense.Data;
using System.Diagnostics;

namespace _153504_Skroba.Application.Services
{
    public class AuthorService : IAuthorService
    {
        private readonly IUnitOfWork _unitOfWork;
        public AuthorService(IUnitOfWork unitOfWork)
        {
            _unitOfWork = unitOfWork;
        }

        public Task<Author> GetByIdAsync(int id)
        {
            return _unitOfWork.AuthorRepository.GetByIdAsync(id);
        }

        public async Task<IReadOnlyList<Author>> GetAllAsync()
        {
            return await _unitOfWork.AuthorRepository.ListAllAsync();
        }

        public async Task AddAsync(Author item)
        {
            await _unitOfWork.AuthorRepository.AddAsync(item);
            await _unitOfWork.SaveAllAsync();
        }

        public Task UpdateAsync(Author item)
        {
            return _unitOfWork.AuthorRepository.UpdateAsync(item);
        }

        public Task DeleteAsync(int id)
        {
            return _unitOfWork.AuthorRepository.DeleteAsync(this.GetByIdAsync(id).Result);
        }

        public Task<IReadOnlyList<Book>> GetAllBooksByAuthorAsync(int id)
        {
            Debug.WriteLine($"\n----------------------лох {_unitOfWork.BookRepository.ListAsync(el => el.AuthorId == id)}");
            return _unitOfWork.BookRepository.ListAsync(el => el.AuthorId == id);
        }

        /*        public async Task<IEnumerable<Author>> GetAuthorsByGenreAsync(string genre)
                {
                    var authors = await _unitOfWork.BookRepository.ListAsync(b => b.Description == genre, includesProperties: b => b.);
                    var uniqueAuthors = authors.Select(b => b.Author).Distinct().ToList();
                    return uniqueAuthors;
                }*/

    }
}
