// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.79804348;
  double density_weight = 0.30781145;
  double prefix_weight = 0.02689790;
  double neighborhood_weight = 0.23464851;
  double late_weight = 0.06852549;
  double critical_weight = 0.37814083;
  unsigned budget = 27;
  unsigned neighborhood = 2;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
