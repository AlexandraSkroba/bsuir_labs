# frozen_string_literal: true

require_relative '../main'

describe 'ex_5' do
  describe 'main' do
    it 'prints an error message if no extension is provided' do
      ARGV.replace [] # simulate no command line argument
      expect(capture_stdout { main }).to include("Please provide an extension as a command line argument.\n")
    end

    it 'searches for files with the specified extension' do
      ARGV.replace ['rb'] # simulate command line argument
      expect(capture_stdout { main }).to include('Files with the .rb extension found:')
    end

    it 'handles invalid extension gracefully' do
      ARGV.replace ['invalid'] # simulate command line argument
      expect(capture_stdout { main }).to include('No files with the .invalid extension found in')
    end

    it 'handles spaces in file names gracefully' do
      ARGV.replace ['txt'] # simulate command line argument
      File.open('with spaces.txt', 'w') # create test file
      expect(capture_stdout { main }).to include('Files with the .txt extension found:')
      File.delete('with spaces.txt') # delete test file
    end

    it 'handles subdirectories gracefully' do
      ARGV.replace ['rb'] # simulate command line argument
      # checks if there are files located deeper than current one
      expect(capture_stdout { main }).to match(%r{#{Dir.pwd}.+/})
    end
  end
end

def capture_stdout
  original_stdout = $stdout # save the original STDOUT for later restoration.
  $stdout = StringIO.new # redirect STDOUT to a StringIO object.
  yield                   # execute the block of code.
  $stdout.string          # return the captured output as a string.
ensure
  $stdout = original_stdout  # restore the original STDOUT.
end
