defmodule Solution do
#Enter your code here. Read input from STDIN. Print output to STDOUT
  def factorial(0), do: 1

  def factorial(num) when num > 0 do
    num * factorial(num - 1)
  end

  def sumatory([head|tail]) do
    {num, _} = head |> Float.parse

    IO.puts(calc_sum(num, 0))
    sumatory(tail)
  end

  def sumatory([]) do
    nil
  end

  def calc_sum(num, acc) when acc >= 0 and acc < 10 do
    :math.pow(num, acc)/factorial(acc) + (calc_sum(num, acc+1))
  end

  def calc_sum(_num, _acc) do
    0
  end
end
