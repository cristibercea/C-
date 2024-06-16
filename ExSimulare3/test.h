#pragma once
class tester
{
public:
	/// <summary>
	/// runs all tests
	/// </summary>
	void runAllTests() const;
private:
	/// <summary>
	/// run entity tests
	/// </summary>
	void runDomainTests() const;

	/// <summary>
	/// run service tests
	/// </summary>
	void runServTests() const;

	/// <summary>
	/// run repository tests
	/// </summary>
	void runRepoTests() const;
};

