using _153504_Skroba.Domain.Abstractions;
using _153504_Skroba.Application.Abstractions;
using _153504_Skroba.Domain.Entities;

namespace _153504_Skroba.Application.Services
{
    public class AuthorService : IAuthorService
    {
        IUnitOfWork _unitOfWork;

        public AuthorService(IUnitOfWork unitOfWork)
        {
            _unitOfWork = unitOfWork;
        }

        public async Task AddAsync(Author item)
        {
            await _unitOfWork.AuthorRepository.AddAsync(item);

            await _unitOfWork.SaveAllAsync();
        }

        public async Task AddBookByAuthor(int authorId, Book book)
        {
            var brigade = await _unitOfWork.AuthorRepository.GetByIdAsync(authorId);
            brigade.Books.Add(book);
        }

        public Task DeleteAsync(int id)
        {
            return _unitOfWork.AuthorRepository.DeleteAsync(this.GetByIdAsync(id).Result);
        }

        public Task DeleteAsync(Author item)
        {
            return _unitOfWork.AuthorRepository.DeleteAsync(item);
        }

        public async Task<IReadOnlyList<Author>> GetAllAsync()
        {
            return await _unitOfWork.AuthorRepository.ListAllAsync();
        }

        public Task<IReadOnlyList<Book>> GetAllBooksByAuthorAsync(int id)
        {
            return _unitOfWork.BookRepository.ListAsync(el => el.AuthorId == id);
        }

        public Task<Author> GetByIdAsync(int id)
        {
            return _unitOfWork.AuthorRepository.GetByIdAsync(id);
        }

        public Task UpdateAsync(Author item)
        {
            return _unitOfWork.AuthorRepository.UpdateAsync(item);
        }
    }
}
