require 'spec_helper'

describe Mpg123 do
  it 'has a version number' do
    expect(Mpg123::VERSION).not_to be nil
  end
end

describe Mpg123::MpegFile do
  it "doesn't throw an error on object creation" do
    expect { Mpg123::MpegFile.new }.not_to raise_error
  end
end
