#! /usr/bin/env ruby

require 'zlib'

log_ids = ["SYSTEM_ID", "SYSTEM_VERSION", "LOGGER_INITIALIZED", "GPIO_INITIALIZED", "SYSTEM_INITIALIZED", "SYSTEM_HALTED", "INFO", "WARNING", "ERROR", "PROFILING_STARTED", "PROFILING_RESULT", "PROFILING_COMPLETED", "DATA_RECEIVED", "DATA_ANALYSIS_STARTED", "DATA_ALPHA_COUNT", "DATA_NUMERIC_COUNT", "DATA_PUNCTUATION_COUNT", "DATA_MISC_COUNT", "DATA_ANALYSIS_COMPLETED", "HEARTBEAT", "CORE_DUMP"]

def SimpleXorCRC(str)
  crc = 0
  str.unpack("C*").each do |e|
    crc ^= e
  end
  return crc
end

if ARGV.size == 0
  puts "usage: log-decode logfile1 [logfile2...]"
  exit
end

ARGV.each do |filename|
  log_array = File.open(filename, "rb").read.split(//)
  until log_array.empty?
    log_data = ""
    # Log item format:
    #  uint32_t timestamp
    #    transmitted as 4 characters - need integer form
    ts_str = log_array.shift(4).join
    log_data += ts_str
    #    lowercase b = LSB first; B for MSB
    timestamp = ts_str.unpack("b8b8b8b8").join.to_i(2)
    #  uint8_t id
    log_id = log_array.shift
    log_data += log_id
    #  uint8_t source_id
    source_id = log_array.shift
    log_data += source_id
    source = "Unknown"
    source = "BBB" if source_id.unpack("C*").first == 1
    source = "KL25Z" if source_id.unpack("C*").first == 16
    source = "HOST" if source_id.unpack("C*").first == 0
    #  uint8_t len
    log_data_len = log_array.shift
    log_data += log_data_len
    log_data_len = log_data_len.unpack("C*").first
    #  uint8_t * payload
    log_payload = log_array.shift(log_data_len).join
    log_data += log_payload
    #  uint32_t crc
    crc = log_array.shift.unpack("C*").first
    unless crc == SimpleXorCRC(log_data)
      puts "[MALFORMED]"
    else
      puts "#{source} - [#{timestamp} : #{log_ids[log_id.unpack("C*").first]}] #{log_payload}"
    end
  end
end
