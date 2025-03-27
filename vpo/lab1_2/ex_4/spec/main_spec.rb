# frozen_string_literal: true

require 'nokogiri' # library to analyze HTML
require_relative '../main'

describe 'ex_4' do
  describe 'main' do
    it 'creates an HTML file' do
      allow(self).to receive(:puts)
      allow(self).to receive(:erb_file_path).and_return('table.html.erb')
      allow(self).to receive(:html_file).and_return('table.html')
      main # run our code
      expect(File.exist?('table.html')).to be(true)
    end

    it 'generates valid HTML content' do
      allow(self).to receive(:puts)
      allow(self).to receive(:erb_file_path).and_return('table.html.erb')
      allow(self).to receive(:html_file).and_return('table.html')
      main
      html_content = File.read('table.html')
      expect { Nokogiri::HTML(html_content) }.not_to raise_error # try to build HTML
    end
  end

  describe 'template file' do
    it 'exists' do
      expect(File.exist?(File.join(__dir__, '../table.html.erb'))).to be(true)
    end

    it 'contains valid ERB syntax' do
      erb_str = File.read(File.join(__dir__, '../table.html.erb'))
      expect { ERB.new(erb_str) }.not_to raise_error
    end
  end

  it 'creates a valid HTML file with 10 rows' do
    allow(self).to receive(:puts) # Suppress console output
    allow(self).to receive(:erb_file_path).and_return('table.html.erb')
    allow(self).to receive(:html_file).and_return('table.html')
    main
    html_content = File.read('table.html')
    expect(Nokogiri::HTML(html_content).css('tr').count).to eq(10)
  end
end

# delete created HTML file
at_exit do
  file_path = 'table.html'
  begin
    File.delete(file_path)
    puts "File '#{file_path}' deleted successfully."
  rescue StandardError => e
    puts "An error occurred: #{e.message}"
  end
end
