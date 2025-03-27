using _153504_Skroba.Application.Abstractions;
using _153504_Skroba.Domain.Abstractions;
using _153504_Skroba.Domain.Entities;


namespace _153504_Skroba.Application.Services
{
    public class BookService : IBookService
    {
        IUnitOfWork _unitOfWork;
        public BookService(IUnitOfWork unitOfWork)
        {
            _unitOfWork = unitOfWork;
        }

        public async Task AddAsync(Book item)
        {
            await _unitOfWork.BookRepository.AddAsync(item);
            await _unitOfWork.SaveAllAsync();
        }

        public async Task DeleteAsync(int id)
        {
            var work = await this.GetByIdAsync(id);

            if (work != null)
            {
                await _unitOfWork.BookRepository.DeleteAsync(work);
            }
        }

        public Task DeleteAsync(Book item)
        {
            return _unitOfWork.BookRepository.DeleteAsync(item);
        }

        public async Task<IReadOnlyList<Book>> GetAllAsync()
        {
            return await _unitOfWork.BookRepository.ListAllAsync();
        }

        public Task<Book> GetByIdAsync(int id)
        {
            return _unitOfWork.BookRepository.GetByIdAsync(id);
        }

        public async Task UpdateAsync(Book item)
        {
            await _unitOfWork.BookRepository.UpdateAsync(item);

            await _unitOfWork.SaveAllAsync();
        }
    }
}
