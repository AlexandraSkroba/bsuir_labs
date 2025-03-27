using _153504_Skroba.Application.Abstractions;
using CommunityToolkit.Mvvm.ComponentModel;
using _153504_Skroba.Domain.Entities;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using CommunityToolkit.Mvvm.Input;
using System.Diagnostics;

namespace _153504_Skroba.UI.ViewModels
{
    public partial class AuthorsViewModel : ObservableObject
    {
        /* Внедрите в созданный класс сервисы: для доступа к данным групп объектов и классам-членам групп */
        private readonly IAuthorService _authorService;
        private readonly IBookService _bookService;

        public AuthorsViewModel(IAuthorService authorService, IBookService bookService)
        {
            _authorService = authorService;
            _bookService = bookService;
        }

        /*Опишите две коллекции – коллекция объектов и коллекция групп объектов. 
         * Эти коллекции будут источником данных для вывода на страницу */
        public ObservableCollection<Author> Authors { get; set; } = new();
        public ObservableCollection<Book> Books { get; set; } = new();

        /* Добавьте поле, описывающее выбранную группу объектов. Используйте атрибут [ObservableProperty] */
        [ObservableProperty]
        Author selectedAuthor;

        /* команды UpdateGroupList и UpdateMembersList, 
         * вызывающие созданные методы (атрибут [RelayCommand]) */
        [RelayCommand]
        async void UpdateGroupList() => await GetAuthors();
        [RelayCommand]
        async void UpdateMembersList() => await GetBooks();

        /* метод, заполняющий данными список групп объектов */
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

        /* метод, заполняющий данными список объектов группы */
        public async Task GetBooks()
        {
            var books = await _authorService.GetAllBooksByAuthorAsync(SelectedAuthor.Id);

            await MainThread.InvokeOnMainThreadAsync(() =>
            {
                Books.Clear();
                foreach (Book book in books)
                {
                    Books.Add(book);
                    Debug.WriteLine($"\n----------------------лох {book}");
                }
            });
        }
    }
}
