# frozen_string_literal: true

require 'open-uri'

def main
  # Check if the user provided the necessary arguments
  if ARGV.length != 2
    puts 'Usage: ruby fetch_and_save.rb [URL] [Save Path]'
    return
  end

  url = ARGV[0]
  save_path = ARGV[1]

  fetch_and_save(url, save_path)
end

def fetch_and_save(url, save_path)
  content = URI.open(url).read # fetch provided url
  File.open(save_path, 'w') { |file| file.write(content) } # create file and save content of url into it
  puts "Document from #{url} saved to #{save_path}."
rescue StandardError => e # catch all non-system errors
  puts "An error occurred: #{e.message}"
end

# run the main function if executed directly
main if __FILE__ == $PROGRAM_NAME
