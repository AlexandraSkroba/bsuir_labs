using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using SQLite;

namespace _153504_Skroba.Domain.Entities
{
    public class Book : Entity
    {
        public string? Title { get; set; }
        public string? Description { get; set; }
        public double Rating { get; set; }
        public int AuthorId { get; set; }

    }
}
