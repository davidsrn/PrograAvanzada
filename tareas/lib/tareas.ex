defmodule Tareas do
  @moduledoc """
  Documentation for Tareas.
  """

  # IO.inspect System.argv

  def main(args) do
    args |> process
  end

  def process([]) do
    IO.puts "No args given"
  end

  def process(args) do

    password = "alumno"

    vdir = tl(args)

    rdir = hd(args)

    files = Path.wildcard("#{rdir}/*")

    System.cmd("sshpass", ["-p", "alumno", "ssh", "alumno@192.168.56.101", "rm /home/alumno/#{vdir}/*"])

    for file <- files do
      filename =
        file
        |> String.split("/")
        |> Enum.at (-1)

      System.cmd("sshpass", ["-p", "#{password}", "scp", "#{file}", "alumno@192.168.56.101:/home/alumno/#{vdir}"])
      System.cmd("sshpass", ["-p", "#{password}", "ssh", "alumno@192.168.56.101",
                  "cp /home/alumno/#{vdir}/#{filename} /home/alumno/grading/simple.c;
                  cp /home/alumno/files/Makefile /home/alumno/grading/Makefile;
                  cd /home/alumno/grading;
                  make;
                  echo #{password} | sudo -S insmod simple.ko;
                  echo #{password} | sudo -S rmmod -f simple;
                  echo \"-----------------------------------\" >> /home/alumno/results/#{filename}.txt;
                  echo \"FILENAME: #{filename}\" >> /home/alumno/results/#{filename}.txt;
                  echo \"-----------------------------------\" >> /home/alumno/results/#{filename}.txt;
                  echo \"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\" >> /home/alumno/results/#{filename}.txt;
                  cat /home/alumno/#{vdir}/#{filename} >> /home/alumno/results/#{filename}.txt;
                  echo \"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\" >> /home/alumno/results/#{filename}.txt;
                  echo \"RESULT:\" >> /home/alumno/results/#{filename}.txt;
                  echo \"-----------------------------------\" >> /home/alumno/results/#{filename}.txt;
                  echo #{password} | sudo -S dmesg -c >> /home/alumno/results/#{filename}.txt;
                  echo \"-----------------------------------\" >> /home/alumno/results/#{filename}.txt;
                  rm /home/alumno/grading/*;
                  cat /home/alumno/results.txt;
                  "])
    end
  end


  IO.puts "DONE"

end
