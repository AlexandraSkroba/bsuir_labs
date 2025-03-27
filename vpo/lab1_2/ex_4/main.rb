# frozen_string_literal: true

require 'erb'

def main
  # this variables are used in .erb file
  num_rows = 18 # number of rows in the table (adjustable)
  color_step = 255.0 / num_rows # calculate color step

  erb_file = 'table.html.erb' # name of file to build HTML from
  erb_file_path = File.join(__dir__, erb_file) # path to this file
  html_file = File.basename(erb_file, '.erb') #=>"table.html"

  erb_str = File.read(erb_file_path) # contents of .erb file

  renderer = ERB.new(erb_str) # create new ERB class instance based on our .erb file contents
  result = renderer.result(binding) # generate HTML using ERB

  # create HTML file
  File.open(html_file, 'w') do |f|
    f.write(result) # fill it with generated HTML
  end
end

# run the main function if executed directly
main if __FILE__ == $PROGRAM_NAME
