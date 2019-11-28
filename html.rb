#!/usr/bin/env ruby
# frozen_string_literal: true

# This script converts HTML files found in ./html into a C header file which can
# be then used inside C code. For example html/index.html will be available as
# HTML_INDEX.

defines = Dir['./html/*.html'].map do |file|
  name = File.basename(file, '.html').upcase
  define = File.readlines(file)
               .map(&:strip)
               .map { |line| line.gsub('"', '\\"') }
               .map { |line| "\"#{line}\"\\" }
               .join("\n")

  <<~C
    #define HTML_#{name} #{define}\n
  C
end

File.write('html.h', defines.join)
