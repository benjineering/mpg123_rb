require 'bundler/gem_tasks'
require 'rspec/core/rake_task'
require 'rake/extensiontask'

RSpec::Core::RakeTask.new(:spec)

Rake::ExtensionTask.new('mpg123') do |ext|
  ext.lib_dir = 'lib/mpg123'
end

Rake::Task[:spec].prerequisites << :compile

task :default => :spec
