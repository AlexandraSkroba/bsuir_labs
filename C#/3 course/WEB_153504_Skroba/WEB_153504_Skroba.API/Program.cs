using Microsoft.AspNetCore.Authentication.JwtBearer;
using Microsoft.EntityFrameworkCore;
using WEB_153504_Skroba.API.Data;
using WEB_153504_Skroba.API.Services.CategoryService;
using WEB_153504_Skroba.API.Services.TeaService;

var builder = WebApplication.CreateBuilder(args);

builder.Configuration.AddJsonFile("appsettings.json");
string connectionString = builder.Configuration.GetConnectionString("Default") ?? "";

builder.Services.AddControllers();
builder.Services.AddDbContext<AppDbContext>(options =>
{
	options.UseSqlite(connectionString);
});

builder.Services
    .AddAuthentication(JwtBearerDefaults.AuthenticationScheme)
    .AddJwtBearer(opt =>
    {
        opt.Authority = builder
        .Configuration
        .GetSection("isUri").Value;
        opt.TokenValidationParameters.ValidateAudience = false;
        opt.TokenValidationParameters.ValidTypes =
        new[] { "at+jwt" };
    });

builder.Services.AddEndpointsApiExplorer();
builder.Services.AddSwaggerGen();

builder.Services.AddScoped<ICategoryService, CategoryService>();
builder.Services.AddScoped<ITeaService, TeaService>();

builder.Services.AddHttpContextAccessor();


builder.Services.AddCors(options => options.AddPolicy("Cors",
            builder =>
            {
                builder.
                AllowAnyOrigin().
                AllowAnyMethod().
                AllowAnyHeader();
            }));

var app = builder.Build();

DbInitializer.SeedData(app).GetAwaiter().GetResult();

// Configure the HTTP request pipeline.
if (app.Environment.IsDevelopment())
{
	app.UseSwagger();
	app.UseSwaggerUI();
}

app.UseHttpsRedirection();

app.UseStaticFiles(); //Для доступа к файлам изображений в классе program добавьте в конвейер Middleware компонент статических файлов

app.UseCors("Cors");

app.UseAuthentication();
app.UseAuthorization();

app.MapControllers();

app.Run();
