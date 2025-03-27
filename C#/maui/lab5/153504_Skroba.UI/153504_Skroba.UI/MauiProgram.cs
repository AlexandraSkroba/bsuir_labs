using _153504_Skroba.Application.Abstractions;
using _153504_Skroba.Application.Services;
using _153504_Skroba.Domain.Abstractions;
using _153504_Skroba.Domain.Entities;
using _153504_Skroba.Persistense.Data;
using _153504_Skroba.Persistense.Repository;
using CommunityToolkit.Maui;
using _153504_Skroba.UI.Pages;
using _153504_Skroba.UI.ViewModels;
using Microsoft.EntityFrameworkCore;
using Microsoft.Extensions.Configuration;
using System.Reflection;
using Microsoft.Extensions.Logging;

namespace _153504_Skroba.UI;

public static class MauiProgram
{
	public static MauiApp CreateMauiApp()
	{
        string settingsStream = "_153504_Skroba.UI.appsettings.json";

        var builder = MauiApp.CreateBuilder();
		builder
			.UseMauiApp<App>()
            .UseMauiCommunityToolkit()
            .ConfigureFonts(fonts =>
			{
				fonts.AddFont("OpenSans-Regular.ttf", "OpenSansRegular");
				fonts.AddFont("OpenSans-Semibold.ttf", "OpenSansSemibold");
			});

        var a = Assembly.GetExecutingAssembly();
        using var stream = a.GetManifestResourceStream(settingsStream);
        builder.Configuration.AddJsonStream(stream);

#if DEBUG
        builder.Logging.AddDebug();
#endif

        SetupServices(builder.Services);
        AddDbContext(builder);
        SeedData(builder.Services);
        return builder.Build();
    }

    private static void SetupServices(IServiceCollection services)
    {
        //Services
        services.AddScoped<IUnitOfWork, EfUnitOfWork>();
        services.AddScoped<IAuthorService, AuthorService>();
        services.AddScoped<IBookService, BookService>();

        //Pages
        services.AddSingleton<Authors>();
        services.AddTransient<BookDetails>();
        services.AddSingleton<AddAuthor>();
        services.AddSingleton<AddBook>();
        services.AddScoped<EditBook>();

        //ViewModels
        services.AddSingleton<AuthorsViewModel>();
        services.AddTransient<BookDetailsViewModel>();
        services.AddTransient<BookEditViewModel>();
    }

    private static void AddDbContext(MauiAppBuilder builder)
    {
        var connStr = builder.Configuration.GetConnectionString("SqliteConnection");
        string dataDirectory = String.Empty;

        #if ANDROID
            dataDirectory = FileSystem.AppDataDirectory+"/";
        #endif

        connStr = String.Format(connStr, dataDirectory);

        var options = new DbContextOptionsBuilder<AppDbContext>()
                .UseSqlite(connStr)
                .UseQueryTrackingBehavior(QueryTrackingBehavior.NoTracking)
                .Options;

        builder.Services.AddSingleton<AppDbContext>((s) => new AppDbContext(options));
    }

    public async static void SeedData(IServiceCollection services)
    {
        using var provider = services.BuildServiceProvider();
        var unitOfWork = provider.GetService<IUnitOfWork>();

        await unitOfWork.RemoveDatbaseAsync();
        await unitOfWork.CreateDatabaseAsync();

        // Add authors
        IReadOnlyList<Author> authors = new List<Author>()
        {
            new Author(){ Name = "Жан Поль Сартр", },
            new Author(){ Name = "Евгений Замятин" }
        };

        foreach (var author in authors)
            await unitOfWork.AuthorRepository.AddAsync(author);

        await unitOfWork.SaveAllAsync();

        //Add books
        Random rand = new Random();
        int k = 1;

        foreach (var author in authors)
            for (int j = 0; j < 5; j++)
            {
                await unitOfWork.BookRepository.AddAsync(new Book()
                {
                    Name = $"Book {k++}",
                    Rating = rand.Next(0, 100) / 10,
                    Year = rand.Next(1990, 2023),
                    AuthorId = author.Id,
                    ImagePath = $"ph{k - 1}.jpg"
                });
            }

        await unitOfWork.SaveAllAsync();
    }

}
