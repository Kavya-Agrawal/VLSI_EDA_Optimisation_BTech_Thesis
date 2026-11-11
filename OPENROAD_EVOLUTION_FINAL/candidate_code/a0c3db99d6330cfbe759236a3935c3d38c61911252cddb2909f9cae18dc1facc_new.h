// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.80399375;
  double density_weight = 0.37613774;
  double prefix_weight = 0.37429806;
  double neighborhood_weight = 0.10060456;
  double late_weight = 0.08611465;
  double critical_weight = 0.42247439;
  unsigned budget = 31;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 1;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
