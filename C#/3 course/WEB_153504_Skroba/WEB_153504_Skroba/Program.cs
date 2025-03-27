using WEB_153504_Skroba.Data;
using WEB_153504_Skroba.Services.CategoryService;
using WEB_153504_Skroba.Services.ProductService;
using WEB_153504_Skroba.Services.TeaService;
using WEB_153504_Skroba.Services.ApiService;
using WEB_153504_Skroba.Services.CartService;
using Microsoft.EntityFrameworkCore;
using WEB_153504_Skroba.API.Data;
using WEB_153504_Skroba;
using WEB_153504_Skroba.TagHelpers;
using WEB_153504_Skroba.Domain.Entities;
using System.Diagnostics;
using Microsoft.AspNetCore.HttpOverrides;
using Serilog;
using Serilog.Events;

var builder = WebApplication.CreateBuilder(args);
builder.Configuration.AddJsonFile("appsettings.json");

builder.Services.AddHttpContextAccessor();
builder.Services.AddAuthentication(opt =>
{
    opt.DefaultScheme = "cookie";
    opt.DefaultChallengeScheme = "oidc";
})
    .AddCookie("cookie")
    .AddOpenIdConnect("oidc", options =>
    {
        options.Authority =
        builder.Configuration["InteractiveServiceSettings:AuthorityUrl"];
        options.ClientId =
        builder.Configuration["InteractiveServiceSettings:ClientId"];
        options.ClientSecret =
        builder.Configuration["InteractiveServiceSettings:ClientSecret"];
        // Получить Claims пользователя
        options.GetClaimsFromUserInfoEndpoint = true;
        options.ResponseType = "code";
        options.ResponseMode = "query";
        options.SaveTokens = true;
    });

// получите UriData из объекта IConfiguration
var uriData = new UriData();
builder.Configuration.GetSection("UriData").Bind(uriData);
builder.Services.AddSingleton(uriData);

// Add services to the container.
builder.Services.AddControllersWithViews();

builder.Services.AddScoped<ICategoryService, ApiCategoryService>();
builder.Services.AddScoped<ITeaService, ApiTeaService>();
builder.Services.AddScoped<PagerTagHelper>();
builder.Services.AddScoped(SessionCart.GetCart);

// Настройка использования Serilog в контексте хоста приложения
builder.Host.UseSerilog((hostingContext, loggerConfiguration) =>
    // Чтение настроек логирования из конфигурации приложения
    loggerConfiguration.ReadFrom.Configuration(hostingContext.Configuration)
        // Добавление фильтра для выборки событий логирования
        .Filter.ByIncludingOnly(evt =>
        {
            // Проверка наличия свойства "StatusCode" и его значения в событии
            if (evt.Properties.TryGetValue("StatusCode", out var statusCodeValue) && statusCodeValue is ScalarValue statusCodeScalar && statusCodeScalar.Value is int statusCode)
            {
                // статус код не в пределах 2xx
                return statusCode < 200 || statusCode >= 300;
            }
            // Возврат false, если свойство "StatusCode" отсутствует или его значение не является целым числом
            return false;
        }));


builder.Services.AddHttpClient<ITeaService, ApiTeaService>(opt => opt.BaseAddress = new Uri(uriData.ApiUri));
builder.Services.AddHttpClient<ICategoryService, ApiCategoryService>(opt => opt.BaseAddress = new Uri(uriData.ApiUri));

builder.Services.AddDistributedMemoryCache();
builder.Services.AddSession();

/*//temp
var connectionString = "Data Source=MenuDb.db";
string dataDirectory = AppDomain.CurrentDomain.BaseDirectory + Path.DirectorySeparatorChar;
connectionString = string.Format(connectionString!, dataDirectory);
builder.Services.AddDbContext<WEB_153504_Skroba.AppDbContext>(options => options.UseSqlite(connectionString).EnableSensitiveDataLogging());
//temp
*/
builder.Services.AddHttpContextAccessor();
builder.Services.AddRazorPages();

var app = builder.Build();

// Configure the HTTP request pipeline.
if (!app.Environment.IsDevelopment())
{
    app.UseExceptionHandler("/Home/Error");
    // The default HSTS value is 30 days. You may want to change this for production scenarios, see https://aka.ms/aspnetcore-hsts.
    app.UseHsts();
}

app.UseLoggingMiddleware();

app.UseHttpsRedirection();
app.UseStaticFiles();

app.UseRouting();
app.UseSession();

app.UseAuthentication();
app.UseAuthorization();

app.MapControllerRoute(
    name: "default",
    pattern: "{controller=Home}/{action=Index}/{id?}");

app.MapRazorPages().RequireAuthorization();

app.Run();
