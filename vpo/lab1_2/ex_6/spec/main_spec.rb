# frozen_string_literal: true

# spec/fetch_and_save_spec.rb

require_relative '../main'

RSpec.describe 'ex_6' do
  describe 'main' do
    it 'fetches content from a valid URL and saves it to a file' do
      url = 'https://example.com'
      save_path = 'example.html'
      allow(URI).to receive(:open).with(url).and_return(StringIO.new('<html><body>Example Content</body></html>'))
      expect { fetch_and_save(url, save_path) }.to output("Document from #{url} saved to #{save_path}.\n").to_stdout
      expect(File.exist?(save_path)).to be(true)
      expect(File.read(save_path)).to eq('<html><body>Example Content</body></html>')
      File.delete(save_path) if File.exist?(save_path)
    end

    it 'handles errors when fetching content from an invalid URL' do
      url = 'https://invalidurl12345.com'
      save_path = 'invalid.html'
      allow(URI).to receive(:open).with(url).and_raise(OpenURI::HTTPError.new('Error', nil))
      expect { fetch_and_save(url, save_path) }.to output(/An error occurred/).to_stdout
      expect(File.exist?(save_path)).to be(false)
    end

    it 'handles errors when saving content to a read-only file path' do
      url = 'https://example.com'
      save_path = '/etc/hosts' # This is a read-only system file
      allow(URI).to receive(:open).with(url).and_return(StringIO.new('<html><body>Example Content</body></html>'))
      expect { fetch_and_save(url, save_path) }.to output(/An error occurred/).to_stdout
    end
  end

  context 'when incorrect number of arguments provided' do
    it 'prints usage instructions when no arguments are provided' do
      ARGV.replace [] # simulate command line argument
      expect(capture_stdout { main }).to include('Usage: ruby fetch_and_save.rb [URL] [Save Path]')
    end

    it 'prints usage instructions when only one argument is provided' do
      ARGV.replace ['https://example.com'] # simulate command line argument
      expect(capture_stdout { main }).to include('Usage: ruby fetch_and_save.rb [URL] [Save Path]')
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
