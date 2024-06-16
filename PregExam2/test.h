#pragma once
class Tester
{
	/// <summary>
	/// ruleaza teste domeniu
	/// </summary>
	void testDomain() const;

	/// <summary>
	/// ruleaza teste repo
	/// </summary>
	void testRepository() const;

	/// <summary>
	/// ruleaza teste serv
	/// </summary>
	void testService() const;
public:
	/// <summary>
	/// ruleaza toate testele
	/// </summary>
	void runAll() const;
};

