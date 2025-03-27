using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Linq;

namespace _153504_Skroba.Domain.Entities
{
    public class Author : Entity
    {
        public List<Book>? Books { get; set; }
    }
}
