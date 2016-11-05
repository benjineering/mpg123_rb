require 'spec_helper'

describe Mpg123 do
  it 'has a version number' do
    expect(Mpg123::VERSION).not_to be nil
  end

  describe '.init' do
    it "doesn't throw an error if called once" do
      expect { Mpg123.init }.not_to raise_error
      Mpg123.exit
    end

    it 'returns 0' do
      expect(Mpg123.init).to eq(0)
      Mpg123.exit
    end
  end

  describe '.exit' do
    it "doesn't throw an error" do
      expect { Mpg123.exit }.not_to raise_error
    end
  end
end

describe Mpg123::Handle do
  describe '.new' do
    it "doesn't throw an error" do
      expect { Mpg123::Handle.new }.not_to raise_error
    end
  end

  describe '#supported_decoders' do
    it 'returns an array containing at least one string' do
      handle = Mpg123::Handle.new
      decoders = handle.supported_decoders
      expect(decoders).to be_a(Array)
      expect(decoders.length).to be > 0
    end
  end

  describe '#decoder' do
    it 'returns a supported decoder' do
      handle = Mpg123::Handle.new
      expect(handle.supported_decoders).to include(handle.decoder)
    end
  end

  describe '#decoder=' do
    it "sets the decoder if it's supported" do
      handle = Mpg123::Handle.new
      current_decoder = handle.decoder
      new_decoder = 
        handle.supported_decoders.delete_if { |d| d == current_decoder }.first
      handle.decoder = new_decoder
      expect(handle.decoder).to eq(new_decoder)
    end

    it "throws an error if the decoder isn't supported" do
      handle = Mpg123::Handle.new
      expect { handle.decoder = 'wizza wuzzle' }.to raise_error(RuntimeError)
    end
  end

  describe '#get_param' do
    it 'returns a number if the type is supported'
    it "throws an error if the type isn't supported"
  end

  describe '#set_param' do
    it 'sets a parameter with an integer value'
    it 'sets a parameter with a float value'
    it "throws an error if the type isn't supported"
  end
end
