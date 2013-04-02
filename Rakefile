
require 'rake'

require 'rspec/core/rake_task'
RSpec::Core::RakeTask.new('spec') do |t|
  t.verbose = true
end

require 'rake/extensiontask'

def gemspec
  @clean_gemspec ||= eval(File.read(File.dirname(__FILE__) + '/deep_clone.gemspec'))
end

Rake::ExtensionTask.new("deep_clone", gemspec) do |ext|
  ext.lib_dir = File.join 'lib', 'deep_clone'
end
Rake::Task[:spec].prerequisites << :compile

BENCHMARKS = Dir["#{File.dirname(__FILE__)}/benchmark/*.rb"].map do |path|
  File.basename(path, '.rb')
end

namespace :bench do
  BENCHMARKS.each do |feature|
      desc "Run #{feature} benchmarks"
      task(feature){ ruby "benchmark/#{feature}.rb" }
  end

  task :all do
    BENCHMARKS.each do |feature|
      ruby "benchmark/#{feature}.rb"
    end
  end
end

