using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;
using WEB_153504_Skroba.API.Data;
using WEB_153504_Skroba.API.Services.TeaService;
using WEB_153504_Skroba.Domain.Entities;
using WEB_153504_Skroba.Domain.Models;

namespace WEB_153504_Skroba.API.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class TeasController : ControllerBase
    {
        private readonly AppDbContext _context;
        private readonly ITeaService _teaService;
        private readonly IWebHostEnvironment _webHostEnvironment;
        private readonly IConfiguration _configuration;

        public TeasController(AppDbContext context, ITeaService teaService, 
            IWebHostEnvironment webHostEnvironment, IConfiguration configuration)
        {
            _context = context;
            _teaService = teaService;
            _webHostEnvironment = webHostEnvironment;
            _configuration = configuration;
        }

        // GET: api/Teas
        //[HttpGet]
        [HttpGet("{pageNo:int?}")]
		[HttpGet("{category}/{pageNo?}")]
        [AllowAnonymous]
        public async Task<ActionResult<ResponseData<List<Tea>>>> GetTeas(string? category, int pageNo = 1, int pageSize = 3)
		{
			return Ok(await _teaService.GetProductListAsync(category, pageNo, pageSize));
		}

		// GET: api/Teas/5
		[HttpGet("id/{id}")]
        [AllowAnonymous]
        public async Task<ActionResult<Tea>> GetTea(int id)
        {
            var response = await _teaService.GetProductByIdAsync(id);
            if (response.Success)
            {
                return Ok(response);
            }

            return NotFound(response);
        }

        // PUT: api/Teas/5
        // To protect from overposting attacks, see https://go.microsoft.com/fwlink/?linkid=2123754
        [HttpPut("put/{id}")]
        [Authorize]
        public async Task<IActionResult> PutTea(int id, Tea tea)
        {
            await _teaService.UpdateProductAsync(id, tea);

            return Ok();
        }

        // POST: api/Teas
        // To protect from overposting attacks, see https://go.microsoft.com/fwlink/?linkid=2123754
        [HttpPost]
        [Authorize]
        public async Task<ActionResult<Tea>> PostTea(Tea tea)
        {
            var response = await _teaService.CreateProductAsync(tea);

            return Created($"/api/teas/{response?.Data?.Id}", response);
        }

        [HttpPost("{id}")]
        [Authorize]
        public async Task<ActionResult<ResponseData<string>>> PostImage(int id, IFormFile formFile)
        {
            var response = await _teaService.SaveImageAsync(id, formFile);
            if (response.Success)
            {
                return Ok(response);
            }
            return NotFound(response);
        }

        // DELETE: api/Teas/5
        [HttpDelete("delete/{id}")]
        [Authorize]
        public async Task<IActionResult> DeleteTea(int id)
        {
            await _teaService.DeleteProductAsync(id);

            return NoContent();
        }

        private bool TeaExists(int id)
        {
            return (_context.Teas?.Any(e => e.Id == id)).GetValueOrDefault();
        }
    }
}
