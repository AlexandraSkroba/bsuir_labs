# frozen_string_literal: true

def main
  # array to store people data
  people = input_people

  # display list of all people
  puts 'List of all people:'
  people.each { |person| puts "#{person[:last_name]} #{person[:first_name]} #{person[:age]}" }

  # calculate statistics and displaying it on the screen
  statistics = age_stats(people)

  # display statistics
  puts "Minimal age: #{statistics[:min]}"
  puts "Maximal age: #{statistics[:max]}"
  puts "Average age: #{statistics[:average]}"
end

def input_people
  people = []

  # handle input from console
  loop do
    people.push(person_info)

    puts 'Do you want to add another person? (y/n)'
    answer = gets.chomp.downcase

    # go to new iteration unless user enters 'y' or 'Y'
    break unless answer == 'y'
  end

  people
end

# get person's information from console
def person_info
  # get first from console
  first_name = valid_input('Enter first name:', /[^a-zA-Z]/, 'First name should consist only of letters')
  # get last name from console
  last_name = valid_input('Enter last name:', /[^a-zA-Z]/, 'Last name should consist only of letters')
  # get age from console and convert it to integer
  age = valid_input('Enter age:', /\D|\d{4,}/, 'Age should be from 0 to 999').to_i

  # return person data
  { first_name:, last_name:, age: }
end

# handle valid input based on provided regexp, that catches unwanted characters
def valid_input(prompt, validation_pattern, error_message)
  loop do
    puts prompt
    # get data from console
    input = gets.chomp # chomp cuts \n

    # return value if no unwanted characters were found
    return input unless input.match?(validation_pattern)

    # this line executes only if input is invalid
    puts error_message
  end
end

# calculate age statistics: minimal, maximal and average
def age_stats(people)
  people_ages = people.map { |person| person[:age] }

  # use ruby array methods to find minimum, maximum and total ages
  min = people_ages.min
  max = people_ages.max
  total = people_ages.sum
  # calculate average age and round it to 2 symbols after point
  average = (total.to_f / people.length).round(2)

  { min:, max:, average:, total: }
end

# run the main function if executed directly
main if __FILE__ == $PROGRAM_NAME
