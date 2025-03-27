using IdentityModel;
using Microsoft.AspNetCore.Identity;
using Microsoft.EntityFrameworkCore;
using Serilog;
using System.Security.Claims;
using WEB_153504_Skroba.IdentityServer.Data;
using WEB_153504_Skroba.IdentityServer.Models;
using Microsoft.Extensions.DependencyInjection;

namespace WEB_153504_Skroba.IdentityServer
{
    public class SeedData
    {

/*        private async static Task CreateRoleIfNotExists(RoleManager<IdentityRole> roleMgr, string role)
        {
            var foundRole = roleMgr.FindByNameAsync(role).Result;
            if (foundRole == null)
            {
                await roleMgr.CreateAsync(new IdentityRole(role));
            }
        }*/

        public async static void EnsureSeedData(WebApplication app)
        {
            using (var scope = app.Services.GetRequiredService<IServiceScopeFactory>().CreateScope())
            {
                var context = scope.ServiceProvider.GetService<ApplicationDbContext>();
                context.Database.Migrate();

                var roleManager = scope.ServiceProvider.GetRequiredService<RoleManager<IdentityRole>>();
                List<string> roles = new()
            {
                "user",
                "admin",
            };

                foreach (var role in roles)
                {
                    roleManager.CreateAsync(new IdentityRole(role));
                }

                var userManager = scope.ServiceProvider.GetRequiredService<UserManager<ApplicationUser>>();
                /*var roleMgr = scope.ServiceProvider.GetRequiredService<RoleManager<IdentityRole>>();*/

/*                await CreateRoleIfNotExists(roleMgr, "user");
                await CreateRoleIfNotExists(roleMgr, "admin");*/

                var alice = userManager.FindByNameAsync("alice").Result;
                if (alice == null)
                {
                    alice = new ApplicationUser
                    {
                        UserName = "alice",
                        Email = "AliceSmith@email.com",
                        EmailConfirmed = true,
                    };
                    var result = userManager.CreateAsync(alice, "Pass123$").Result;
                    if (!result.Succeeded)
                    {
                        throw new Exception(result.Errors.First().Description);
                    }

                    result = userManager.AddClaimsAsync(alice, new Claim[]{
                            new Claim(JwtClaimTypes.Name, "Alice Smith"),
                            new Claim(JwtClaimTypes.GivenName, "Alice"),
                            new Claim(JwtClaimTypes.FamilyName, "Smith"),
                            new Claim(JwtClaimTypes.WebSite, "http://alice.com"),
                        }).Result;
                    if (!result.Succeeded)
                    {
                        throw new Exception(result.Errors.First().Description);
                    }
                    Log.Debug("alice created");
                }
                else
                {
                    Log.Debug("alice already exists");
                }

                /*var user = userManager.FindByNameAsync("user").Result;
                if (user == null)
                {
                    user = new ApplicationUser
                    {
                        UserName = "user",
                        Email = "user@gmail.com",
                        EmailConfirmed = true,
                    };
                    var result = userManager.CreateAsync(user, "Pass123$").Result;
                    if (!result.Succeeded)
                    {
                        throw new Exception(result.Errors.First().Description);
                    }

                    result = userManager.AddClaimsAsync(user, new Claim[]{
                            new Claim(JwtClaimTypes.Name, "user"),
                            new Claim(JwtClaimTypes.GivenName, "user"),
                            new Claim(JwtClaimTypes.FamilyName, "user"),
                            new Claim(JwtClaimTypes.WebSite, "http://user.com"),
                            new Claim(JwtClaimTypes.Role, "user")
                        }).Result;
                    if (!result.Succeeded)
                    {
                        throw new Exception(result.Errors.First().Description);
                    }
                    Log.Debug("user created");
                }
                else
                {
                    Log.Debug("user already exists");
                }

                var admin = userManager.FindByNameAsync("admin").Result;
                if (admin == null)
                {
                    admin = new ApplicationUser
                    {
                        UserName = "admin",
                        Email = "admin@gmail.com",
                        EmailConfirmed = true,
                    };
                    var result = userManager.CreateAsync(admin, "Pass123$").Result;
                    if (!result.Succeeded)
                    {
                        throw new Exception(result.Errors.First().Description);
                    }

                    result = userManager.AddClaimsAsync(admin, new Claim[]{
                            new Claim(JwtClaimTypes.Name, "admin"),
                            new Claim(JwtClaimTypes.GivenName, "admin"),
                            new Claim(JwtClaimTypes.FamilyName, "admin"),
                            new Claim(JwtClaimTypes.WebSite, "http://admin.com"),
                            new Claim(JwtClaimTypes.Role, "admin")
                        }).Result;
                    if (!result.Succeeded)
                    {
                        throw new Exception(result.Errors.First().Description);
                    }
                    Log.Debug("admin created");
                }
                else
                {
                    Log.Debug("admin already exists");
                }*/

                var user = userManager.FindByEmailAsync("user@gmail.com").Result;
            if (user == null)
            {
                user = new ApplicationUser
                {
                    UserName = "fakeuser",
                    Email = "user@gmail.com",
                    EmailConfirmed = true
                };

                var result = userManager.CreateAsync(user, "Pass123$").Result;
                if (!result.Succeeded)
                {
                    throw new Exception(result.Errors.First().Description);
                }

                result = userManager.AddClaimsAsync(alice, new Claim[]{
                            new Claim(JwtClaimTypes.Name, "fakeuser"),
                            new Claim(JwtClaimTypes.GivenName, "user"),
                            new Claim(JwtClaimTypes.FamilyName, "user"),
                        }).Result;
                if (!result.Succeeded)
                {
                    throw new Exception(result.Errors.First().Description);
                }
                Log.Debug("user created");
                    userManager.AddToRoleAsync(user, "user");
            }
            else
            {
                Log.Debug("user already exists");
            }


            var admin = userManager.FindByEmailAsync("admin@gmail.com").Result;
            if (admin == null)
            {
                admin = new ApplicationUser
                {
                    UserName = "fakeadmin",
                    Email = "admin@gmail.com",
                    EmailConfirmed = true
                };

                var result = userManager.CreateAsync(admin, "Pass123$").Result;
                if (!result.Succeeded)
                {
                    throw new Exception(result.Errors.First().Description);
                }

                result = userManager.AddClaimsAsync(alice, new Claim[]{
                            new Claim(JwtClaimTypes.Name, "admin"),
                            new Claim(JwtClaimTypes.GivenName, "admin"),
                            new Claim(JwtClaimTypes.FamilyName, "admin"),
                        }).Result;
                if (!result.Succeeded)
                {
                    throw new Exception(result.Errors.First().Description);
                }
                Log.Debug("admin created");
                    userManager.AddToRoleAsync(admin, "admin");
            }
            else
            {
                Log.Debug("admin already exists");
            }

            }
        }
    }
}