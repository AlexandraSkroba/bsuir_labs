using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using _153504_Skroba.Application.Abstractions;
using _153504_Skroba.Domain.Abstractions;
using _153504_Skroba.Domain.Entities;
using _153504_Skroba.Persistense;

namespace _153504_Skroba.Application.Services
{
    public class BookService : IBookService
    {
        private readonly IUnitOfWork _unitOfWork;

        public BookService(IUnitOfWork unitOfWork)
        {
            _unitOfWork = unitOfWork;
        }

        public async Task<IReadOnlyList<Book>> GetAllAsync()
        {
           return await _unitOfWork.BookRepository.ListAllAsync();
        }
        public Task<Book> GetByIdAsync(int id)
        {
            return _unitOfWork.BookRepository.GetByIdAsync(id);
        }
        public async Task AddAsync(Book item)
        {
            await _unitOfWork.BookRepository.AddAsync(item);
            await _unitOfWork.SaveAllAsync();
        }
        public async Task UpdateAsync(Book item)
        {
            await _unitOfWork.BookRepository.UpdateAsync(item);
            await _unitOfWork.SaveAllAsync();
        }
        public async Task DeleteAsync(int id)
        {
            // Получаем книги по идентификатору
            var book = await this.GetByIdAsync(id);

            if(book != null)
            {
                await _unitOfWork.BookRepository.DeleteAsync(book);
            }

        }
    }
}
