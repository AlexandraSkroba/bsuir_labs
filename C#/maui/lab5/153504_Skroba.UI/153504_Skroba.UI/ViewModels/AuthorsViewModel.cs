using _153504_Skroba.Application.Abstractions;
using _153504_Skroba.Domain.Entities;
using _153504_Skroba.UI.Pages;
using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using System.Collections.ObjectModel;

namespace _153504_Skroba.UI.ViewModels
{
    public partial class AuthorsViewModel : ObservableObject
    {
        private IAuthorService _authorService;
        private IBookService _bookService;

        public AuthorsViewModel(IAuthorService authorService, IBookService bookService)
        {
            _authorService = authorService;
            _bookService = bookService;
        }

        public ObservableCollection<Author> Authors { get; set; } = new();
        public ObservableCollection<Book> Books { get; set; } = new();

        [ObservableProperty]
        Author selectedAuthor;

        [RelayCommand]
        public async void UpdateGroupList() => await GetAuthors();

        [RelayCommand]
        public async void UpdateMembersList() => await GetBooks();

        [RelayCommand]
        public async void ShowDetails(Book book) => await GotoDetailsPage(book);

        private async Task GotoDetailsPage(Book book)
        {
            IDictionary<string, object> parameters = new Dictionary<string, object>
            {
                { "Book", book }
            };

            await Shell.Current.GoToAsync(nameof(BookDetails), parameters);
        }

        public async Task GetAuthors()
        {
            var authors = await _authorService.GetAllAsync();

            await MainThread.InvokeOnMainThreadAsync(() =>
            {
                Authors.Clear();
                foreach (Author author in authors)
                    Authors.Add(author);
            });
        }
        public async Task GetBooks()
        {
            var books = await _authorService.GetAllBooksByAuthorAsync(SelectedAuthor.Id);

            await MainThread.InvokeOnMainThreadAsync(() =>
            {
                Books.Clear();
                foreach (Book book in books)
                    Books.Add(book);
            });
        }

        [RelayCommand]
        public async void AddBook() => await GotoAddBook();

        public async Task GotoAddBook()
        {
            await Shell.Current.GoToAsync(nameof(AddBook));
        }

        [RelayCommand]
        public async void AddAuthor() => await GotoAddAuthor();

        public async Task GotoAddAuthor()
        {
            await Shell.Current.GoToAsync(nameof(AddAuthor));
        }

        public async Task AddAuthorAsync(Author author)
        {
            await _authorService.AddAsync(author);

            SelectedAuthor ??= new Author();

            UpdateGroupList();

            await Shell.Current.GoToAsync("///Authors"); // System.Exception: "Relative routing to shell elements is currently not supported. Try prefixing your uri with ///: ///Authors"
        }

        public async Task AddBookAsync(Book book)
        {
            await _bookService.AddAsync(book);

            SelectedAuthor ??= new Author();

            UpdateMembersList();

            await Shell.Current.GoToAsync("///Authors"); //System.Exception: "Relative routing to shell elements is currently not supported. Try prefixing your uri with ///: ///Authors"
        }

        public async Task UpdateBookAsync(Book book)
        {
            await _bookService.UpdateAsync(book);

            SelectedAuthor ??= new Author();

            UpdateMembersList();

            await Shell.Current.GoToAsync("///Authors");
        }
    }
}
