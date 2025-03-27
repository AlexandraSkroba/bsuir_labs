# frozen_string_literal: true

require_relative '../main'

describe 'ex_2' do
  # silence console output
  before do
    allow(self).to receive(:puts)
  end

  describe 'input_people' do
    it 'should add a person to the list' do
      # mock method person_info
      allow(self).to receive(:person_info).and_return({ first_name: 'John', last_name: 'Doe', age: 30 })
      expect(input_people).to eq([{ first_name: 'John', last_name: 'Doe', age: 30 }])
    end
  end

  describe 'person_info' do
    it 'should return person information' do
      allow(self).to receive(:valid_input).and_return('John', 'Doe', '30')
      expect(person_info).to eq({ first_name: 'John', last_name: 'Doe', age: 30 })
    end
  end

  describe 'valid_input' do
    it 'should return valid input' do
      # mock user inout
      allow(self).to receive(:gets).and_return('John')
      expect(valid_input('Enter first name:', /[^a-zA-Z]/, 'Error')).to eq('John')
    end

    it 'should handle invalid input' do
      allow(self).to receive(:gets).and_return('123', 'John')
      expect(valid_input('Enter first name:', /[^a-zA-Z]/, 'Error')).to eq('John')
    end
  end

  describe 'age_stats' do
    it 'should calculate age statistics' do
      people = [
        { first_name: 'John', last_name: 'Doe', age: 30 },
        { first_name: 'Jane', last_name: 'Doe', age: 25 }
      ]
      expect(age_stats(people)).to eq({ min: 25, max: 30, average: 27.5, total: 55 })
    end
  end
end
