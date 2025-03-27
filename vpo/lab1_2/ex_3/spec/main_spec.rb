# frozen_string_literal: true

require_relative '../main'

describe 'ex_3' do
  # silence console output
  before do
    allow(self).to receive(:puts)
  end

  describe 'handle_attr_input' do
    it 'returns a positive integer ' do
      allow(self).to receive(:gets).and_return('5')
      expect(handle_attr_input(:test)).to eq(5)
    end

    it 'rejects a negative number' do
      allow(self).to receive(:gets).and_return('-3')
      expect(handle_attr_input(:test)).not_to be(Integer)
    end

    it 'rejects a zero' do
      allow(self).to receive(:gets).and_return('0')
      expect(handle_attr_input(:test)).not_to be(Integer)
    end

    it 'handles non-integer input gracefully' do
      allow(self).to receive(:gets).and_return('abc')
      expect(handle_attr_input(:test)).not_to be(Integer)
    end
  end

  describe 'calculate_square' do
    it 'calculates the square of a rectangle' do
      expect(calculate_square(3, 5)).to eq(15)
    end
  end
end
