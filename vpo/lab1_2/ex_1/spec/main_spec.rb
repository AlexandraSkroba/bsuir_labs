# frozen_string_literal: true

# frozen string literal comment prevents from modifying strings

require_relative '../main' # load file that we are going to test

ADDITIONAL_EXCLAMATION_MARKS = 2 # exclamations from other lines
MIN_EXCLAMATION_MARKS = 5 # minimum required exclamations
MAX_EXCLAMATION_MARKS = 50 # maximum allowed exclamations

describe 'ex_1' do # name group of tests
  it 'prints at least 5 and at most 50 exclamation marks' do # name specific test
    output = capture_stdout { main } # save method output to output variable
    exclamation_count = output.count('!') # count exclamations

    # test fails if there are less exclamations than allowed
    expect(exclamation_count).to be >= (MIN_EXCLAMATION_MARKS - ADDITIONAL_EXCLAMATION_MARKS)
    # test fails if there are more exclamations than allowed
    expect(exclamation_count).to be <= (MAX_EXCLAMATION_MARKS - ADDITIONAL_EXCLAMATION_MARKS)
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
