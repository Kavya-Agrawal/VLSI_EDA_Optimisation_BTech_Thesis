// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.15137738;
  double density_weight = 0.06199507;
  double prefix_weight = 0.26171759;
  double neighborhood_weight = 0.27471765;
  double late_weight = 0.23250521;
  double critical_weight = 0.13692075;
  unsigned budget = 23;
  unsigned neighborhood = 7;
  unsigned spatial_mode = 1;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
