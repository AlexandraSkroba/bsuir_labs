# frozen_string_literal: true

def main
  width = handle_attr_input :width
  length = handle_attr_input :length

  square = calculate_square(width, length)

  puts "Rectangle square is #{square}"
end

def handle_attr_input(attr_name)
  loop do
    puts "Enter #{attr_name}"
    attr_value = gets.chomp

    # return input value only if it is a positive number
    return attr_value.to_i unless attr_value.match?(/\D/) && attr_value.to_i.positive?

    puts 'Value must be positive number'
  end
end

def calculate_square(width, length)
  width * length
end

# run the main function if executed directly
main if __FILE__ == $PROGRAM_NAME
