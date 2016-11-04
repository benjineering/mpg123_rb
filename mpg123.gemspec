# coding: utf-8
lib = File.expand_path('../lib', __FILE__)
$LOAD_PATH.unshift(lib) unless $LOAD_PATH.include?(lib)
require 'mpg123/version'

Gem::Specification.new do |spec|
  spec.name          = 'mpg123'
  spec.version       = Mpg123::VERSION
  spec.authors       = [ 'Ben Williams' ]
  spec.email         = [ '8enwilliams@gmail.com' ]

  spec.summary       = 'A Ruby gem wrapper for libmpg123'
  spec.description   = 'Provides a simple interface for the mpg123 MPEG library'
  spec.homepage      = 'https://github.com/benjineering/mpg123_rb'

  spec.files         = `git ls-files -z`.split("\x0").reject do |f|
    f.match(%r{^(test|spec|features)/})
  end

  spec.bindir        = 'exe'
  spec.executables   = spec.files.grep(%r{^exe/}) { |f| File.basename(f) }
  spec.require_paths = ['lib']
  spec.extensions       << 'ext/mpg123/extconf.rb'

  spec.add_development_dependency 'bundler',       '~> 1.13'
  spec.add_development_dependency 'rake',          '~> 10.0'
  spec.add_development_dependency 'rake-compiler', '~> 1.0'
  spec.add_development_dependency 'rspec',         '~> 3.0'
end
