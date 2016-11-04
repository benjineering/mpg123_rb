require 'spec_helper'

describe Mpg123 do
  it 'has a version number' do
    expect(Mpg123::VERSION).not_to be nil
  end

  it 'compiles the c extension' do
    expect(Mpg123.mike_check).to eq('moon river')
  end
end
