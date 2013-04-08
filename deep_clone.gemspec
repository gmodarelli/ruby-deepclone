Gem::Specification.new do |s|
  s.specification_version = 2 if s.respond_to? :specification_version=
  s.required_rubygems_version = Gem::Requirement.new(">= 0") if s.respond_to? :required_rubygems_version=
  s.rubygems_version = '1.3.5'

  s.name = 'ruby_deep_clone'
  s.version = '0.1.0'
  s.date = '2013-04-03'

  s.summary = "Ruby native deep clone"
  s.description = "Native implementation to create deep clones of Ruby objects"

  s.authors = ["Matthias Balmer", "Andre Medeiros"]
  s.email = ['balmma@sysinf.ch', 'me@andremedeiros.info']

  s.extensions = ["ext/deep_clone/extconf.rb"]

  s.require_paths = ["ext", "lib"]

  s.files = ["deep_clone.gemspec","lib/deep_clone.rb","ext/deep_clone/deep_clone.c","ext/deep_clone/deep_clone.h","ext/deep_clone/extconf.rb"]

  s.add_development_dependency 'rspec', '~> 2.13.0'
  s.add_development_dependency 'rake-compiler', '~> 0.8.3'
  s.add_development_dependency 'rake', '~> 10.0.4'
end
