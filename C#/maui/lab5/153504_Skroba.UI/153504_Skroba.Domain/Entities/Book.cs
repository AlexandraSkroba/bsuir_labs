using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _153504_Skroba.Domain.Entities
{
    public class Book : Entity
    {
        public string? Genre { get; set; }
        public int Year { get; set; }
        public int AuthorId { get; set; }
        public double Rating { get; set; }
        public String? ImagePath { get; set; }
    }
}
