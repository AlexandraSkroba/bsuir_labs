# frozen_string_literal: true

# this program searches for files with a specified extension in a given directory and its subdirectories.
# the extension is provided as a command line argument. The search results are printed to the console.
# usage: ruby ex_5/main.rb rb

require 'find'

def main
  # check if the user provided an extension as a command line argument
  if ARGV.empty?
    puts 'Please provide an extension as a command line argument.'
    return
  end

  # get the specified extension from the command line argument
  extension = ARGV[0]

  # get the current directory
  current_directory = Dir.pwd

  # initialize an array to store the found file paths
  found_files = []

  # recursive search for files with the specified extension
  Find.find(current_directory) do |path|
    found_files << path if File.file?(path) && File.extname(path) == ".#{extension}"
  end

  # print the search results
  if found_files.empty?
    puts "No files with the .#{extension} extension found in #{current_directory} and its subdirectories."
  else
    puts "Files with the .#{extension} extension found:"
    found_files.each { |file| puts file }
  end
end

# run the main function if executed directly
main if __FILE__ == $PROGRAM_NAME
