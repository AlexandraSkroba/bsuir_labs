# frozen_string_literal: true

6.times do |i|
  system("rspec ex_#{i + 1}/spec/main_spec.rb -f d")
end
