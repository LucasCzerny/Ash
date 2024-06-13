namespace Ash
{
	template <typename T>
	T& Event::Cast()
	{
		return (T&)*this;
	}
}